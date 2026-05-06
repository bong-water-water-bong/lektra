---@meta

lektra = lektra or {}
lektra.cmd = {}

---@class CommandEntry
---@field name string The name of the command.
---@field desc? string A description of the command.

--- Registers a command with the given name and callback function.
---@overload fun(arg: {name: string, callback: function, desc?: string})
---@param name string The name of the command to register.
---@param callback function The function to call when the command is executed. It should accept a single argument, which is a table of the command's arguments.
---@param desc? string A description of the command, which will be shown in the help menu.
lektra.cmd.register = function(name, callback, desc) end

--- Unregisters a command with the given name.
---@overload fun(arg: {name: string})
---@param name string The name of the command to unregister.
lektra.cmd.unregister = function(name) end

--- Executes a command with the given name and arguments.
---@overload fun(arg: {name: string, args?: table}): boolean
---@param name string The name of the command to execute.
---@param args? table A table of arguments to pass to the command's callback function.
---@return boolean True if the command was found and executed successfully, false otherwise.
lektra.cmd.execute = function(name, args) end

--- Lists all registered commands.
---@return table CommandEntry[] table of all registered commands
lektra.cmd.list = function() end

--- Creates an alias for a command.
---@param name string The name of the alias to create.
---@param target string The name of the command that the alias should point to.
lektra.cmd.alias = function(name, target) end
