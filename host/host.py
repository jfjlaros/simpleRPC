from simple_rpc import Interface


interface = Interface('/dev/ttyACM0')

print(interface.testInt())
print(interface.testFloat())
print(interface.add(1, 2))
interface.setLed(10)
