x = package.loadlib("lua_egpkg.dll", "luaopen_egpkg")
x()
print(egpkg.calculayt(3, 1))
print(egpkg.whatever("great example"))