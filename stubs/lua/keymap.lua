---@meta

lektra = lektra or {}
lektra.keymap = {}

--- Sets a key mapping in Lektra.
---@param name string The name of the key mapping (e.g., "save", "open", "close").
---@param value string The key combination to trigger the action (e.g., "Ctrl+S", "Ctrl+O", "Ctrl+W").
lektra.keymap.set = function(name, value) end

--- Unsets a key mapping in Lektra.
---@param name string The name of the key mapping to unset (e.g., "save", "open", "close").
lektra.keymap.unset = function(name) end
