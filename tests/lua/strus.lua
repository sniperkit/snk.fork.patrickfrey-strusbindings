local strus_init,err = package.loadlib("libstrus_bindings_lua.so","luaopen_strus")
if not strus_init then
	error( err)
end
strus_init()

