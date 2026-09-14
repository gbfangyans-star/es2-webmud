# Player Observation Layer
Browser HUD is observation-only. It parses only values visibly emitted by canonical ES2 commands. It never calculates HP, damage, armor, skills, conditions, death, or inventory state from formulas. Unknown output remains in the terminal. Death/combat text matching is cosmetic only and never changes server state.
