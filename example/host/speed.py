from sys import stdout
from time import time

from simple_rpc import Interface


interface = Interface('/dev/ttyACM0')
cycles = 20

stdout.write("Starting speed test ({} cycles) ".format(cycles))
stdout.flush()

start_time = time()
for _ in range(cycles):
    for i in range(256):
        interface.set_led(i)
    for i in range(256)[::-1]:
        interface.set_led(i)
    stdout.write('.')
    stdout.flush()

calls = 512 * cycles
duration = time() - start_time
stdout.write('\n{} calls in {:.02f} seconds ({} calls/sec)\n'.format(
    calls, duration, int(calls // duration)))
