---@meta

lektra = lektra or {}
lektra.mousemap = {}

--- Sets a mouse mapping in Lektra.
---@param name string The name of the mouse mapping (e.g., "preview", "pan", "zoom").
---@param value string The mouse action to trigger the mapping (e.g., "LeftButton", "RightButton", "MiddleButton") + optional modifiers (e.g., "Ctrl", "Shift").
lektra.mousemap.set = function(name, value) end

--- Unsets a mouse mapping in Lektra.
---@param name string The name of the mouse mapping to unset (e.g., "preview", "pan", "zoom").
lektra.mousemap.unset = function(name) end
