---@meta
lektra = lektra or {}
lektra.utils = {}

--- Pretty prints a Lua value to the console, similar to `print` but with better formatting for tables and other complex types
---@overload fun(arg: any)
---@param ... any
lektra.utils.print = function (...) end

--- Opens the specified URL in the user's default web browser.
---@param url string The URL to open
lektra.utils.open_url = function (url) end

--- Returns the operating system platform name
---@return string platform Can be one of "linux" | "windows" | "macos" | "unknown"
lektra.utils.platform = function () end

