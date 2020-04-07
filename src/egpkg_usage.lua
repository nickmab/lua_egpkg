x = package.loadlib("lua_egpkg.dll", "luaopen_egpkg")
x()
print(egpkg.mafematikz.calculayt(3, 1))
print(egpkg.sztryng.whatever("great example"))
print(egpkg.stateful.statefulA())
print(egpkg.stateful.statefulA())
print(egpkg.stateful.statefulB())
print(egpkg.stateful.statefulA())
print(egpkg.stateful.statefulB())
print(egpkg.mafematikz.max(4, -2.5, "6.6", 1.1))
print(egpkg.mafematikz.max())

a = egpkg.array.new(10)
print(a)
a[7] = 22
print(a[7])
a['newkey'] = 77
print(a[8])
print(a['newkey'])

a:set(3, 77)
print("Get item 3: " .. a:get(3))

print("Array size is " .. a:size())
print("There are " .. a:countNonZero() .. " nonzero elements.")

for k,v in a:iter() do
    print("Array elem at key " .. k .. " is " .. v)
end