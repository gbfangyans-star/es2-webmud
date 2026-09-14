param(
  [string]$ListenAddress = "0.0.0.0",
  [int]$ListenPort = 4002,
  [string]$MudHost = "127.0.0.1",
  [int]$MudPort = 4001
)

$ErrorActionPreference = "Stop"

$source = @'
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

public sealed class TelnetTranscoder
{
    private const byte IAC = 255;
    private const byte WILL = 251;
    private const byte WONT = 252;
    private const byte DO = 253;
    private const byte DONT = 254;
    private const byte SB = 250;
    private const byte SE = 240;

    private enum State { Data, Iac, IacOption, Subneg, SubnegIac }

    private readonly Stream input;
    private readonly Stream output;
    private readonly Decoder decoder;
    private readonly Encoder encoder;
    private State state = State.Data;
    private readonly byte[] readBuffer = new byte[4096];
    private readonly byte[] dataBuffer = new byte[4096];
    private int dataCount = 0;

    public TelnetTranscoder(Stream input, Stream output, Encoding sourceEncoding, Encoding targetEncoding)
    {
        this.input = input;
        this.output = output;
        this.decoder = sourceEncoding.GetDecoder();
        this.encoder = targetEncoding.GetEncoder();
    }

    private void FlushText(bool final)
    {
        if (dataCount == 0 && !final) return;

        char[] chars = new char[Math.Max(16, dataCount * 2 + 8)];
        int bytesUsed, charsUsed;
        bool completed;
        decoder.Convert(dataBuffer, 0, dataCount, chars, 0, chars.Length, final,
                        out bytesUsed, out charsUsed, out completed);
        dataCount = 0;

        if (charsUsed > 0)
        {
            byte[] encoded = new byte[Math.Max(32, charsUsed * 4 + 16)];
            int charsConsumed, bytesWritten;
            bool encCompleted;
            encoder.Convert(chars, 0, charsUsed, encoded, 0, encoded.Length, final,
                            out charsConsumed, out bytesWritten, out encCompleted);
            if (bytesWritten > 0) output.Write(encoded, 0, bytesWritten);
        }
        output.Flush();
    }

    private void WriteRaw(byte b)
    {
        output.WriteByte(b);
    }

    private void AddData(byte b)
    {
        if (dataCount >= dataBuffer.Length) FlushText(false);
        dataBuffer[dataCount++] = b;
    }

    public void Run()
    {
        try
        {
            while (true)
            {
                int n = input.Read(readBuffer, 0, readBuffer.Length);
                if (n <= 0) break;

                for (int i = 0; i < n; i++)
                {
                    byte b = readBuffer[i];
                    switch (state)
                    {
                        case State.Data:
                            if (b == IAC)
                            {
                                FlushText(false);
                                WriteRaw(b);
                                state = State.Iac;
                            }
                            else AddData(b);
                            break;

                        case State.Iac:
                            WriteRaw(b);
                            if (b == WILL || b == WONT || b == DO || b == DONT)
                                state = State.IacOption;
                            else if (b == SB)
                                state = State.Subneg;
                            else
                                state = State.Data;
                            break;

                        case State.IacOption:
                            WriteRaw(b);
                            state = State.Data;
                            break;

                        case State.Subneg:
                            WriteRaw(b);
                            if (b == IAC) state = State.SubnegIac;
                            break;

                        case State.SubnegIac:
                            WriteRaw(b);
                            if (b == SE) state = State.Data;
                            else state = State.Subneg;
                            break;
                    }
                }
                FlushText(false);
            }
        }
        catch (IOException) { }
        catch (SocketException) { }
        catch (ObjectDisposedException) { }
        finally
        {
            try { FlushText(true); } catch { }
        }
    }
}

public static class ZmudBig5Bridge
{
    public static void Run(string listenAddress, int listenPort, string mudHost, int mudPort)
    {
        Encoding big5 = Encoding.GetEncoding(950, EncoderFallback.ReplacementFallback, DecoderFallback.ReplacementFallback);
        Encoding utf8 = new UTF8Encoding(false, false);

        IPAddress ip;
        if (!IPAddress.TryParse(listenAddress, out ip))
            ip = Dns.GetHostAddresses(listenAddress)[0];

        TcpListener listener = new TcpListener(ip, listenPort);
        listener.Start();
        Console.WriteLine("[ZMUD] Big5 bridge listening on {0}:{1}", listenAddress, listenPort);
        Console.WriteLine("[ZMUD] Forwarding to Neolith UTF-8 {0}:{1}", mudHost, mudPort);
        Console.WriteLine("[ZMUD] zMUD 4.62 clients should connect to port {0}", listenPort);

        while (true)
        {
            TcpClient client = listener.AcceptTcpClient();
            client.NoDelay = true;
            ThreadPool.QueueUserWorkItem(delegate(object ignored)
            {
                TcpClient mud = null;
                try
                {
                    mud = new TcpClient();
                    mud.NoDelay = true;
                    mud.Connect(mudHost, mudPort);
                    Console.WriteLine("[ZMUD] Client {0} connected", client.Client.RemoteEndPoint);

                    NetworkStream clientStream = client.GetStream();
                    NetworkStream mudStream = mud.GetStream();

                    TelnetTranscoder mudToClient = new TelnetTranscoder(mudStream, clientStream, utf8, big5);
                    TelnetTranscoder clientToMud = new TelnetTranscoder(clientStream, mudStream, big5, utf8);

                    Thread t1 = new Thread(delegate()
                    {
                        try { mudToClient.Run(); }
                        finally
                        {
                            try { client.Close(); } catch { }
                            try { mud.Close(); } catch { }
                        }
                    });
                    Thread t2 = new Thread(delegate()
                    {
                        try { clientToMud.Run(); }
                        finally
                        {
                            try { client.Close(); } catch { }
                            try { mud.Close(); } catch { }
                        }
                    });
                    t1.IsBackground = true;
                    t2.IsBackground = true;
                    t1.Start();
                    t2.Start();
                    t1.Join();
                    t2.Join();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("[ZMUD] Session error: " + ex.Message);
                }
                finally
                {
                    try { client.Close(); } catch { }
                    try { if (mud != null) mud.Close(); } catch { }
                    Console.WriteLine("[ZMUD] Client disconnected");
                }
            });
        }
    }
}
'@

try {
  Add-Type -TypeDefinition $source -Language CSharp
} catch {
  if ($_.Exception.Message -notmatch 'already exists') { throw }
}

Write-Host "============================================================"
Write-Host "ES2 zMUD 4.62 Big5 <-> UTF-8 bridge"
Write-Host "Listen:  $ListenAddress`:$ListenPort  (Big5 / CP950)"
Write-Host "Neolith: $MudHost`:$MudPort          (UTF-8)"
Write-Host "============================================================"
Write-Host "Local zMUD: 127.0.0.1 port $ListenPort"
Write-Host "Remote zMUD: YOUR_PUBLIC_IP port $ListenPort"
Write-Host "For remote players, forward TCP $ListenPort on your router and allow it in Windows Firewall."
Write-Host ""

[ZmudBig5Bridge]::Run($ListenAddress, $ListenPort, $MudHost, $MudPort)
