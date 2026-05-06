---@meta
lektra = lektra or {}
lektra.utils = {}

--- Pretty prints a Lua value to the console, similar to `print` but with better formatting for tables and other complex types
---@overload fun(arg: any)
---@param ... any
lektra.utils.print = function (...) end
