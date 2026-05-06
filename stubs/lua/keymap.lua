---@meta

lektra = lektra or {}
lektra.keymap = {}

--- Sets a key mapping in Lektra.
---@overload fun(name: string, keys: string[])
---@param name string The name of the key mapping (e.g., "save", "open", "close").
---@param keys string[] An array of key combinations to associate with the specified action (e.g., {"Ctrl+S", "Cmd+S"}).
lektra.keymap.set = function(name, keys) end

--- Unsets key mappings of command in Lektra.
---@param name string The name of the key mapping to unset (e.g., "save", "open", "close").
lektra.keymap.unset = function(name) end

--- Retrieves the key mapping for a given action in Lektra.
---@param name string The name of the key mapping to retrieve (e.g., "save", "open", "close").
---@return string[] keys An array of key combinations associated with the specified action. If no mapping exists, returns an empty array.
lektra.keymap.get = function(name) end
