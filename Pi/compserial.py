import xbee, time
# Set the network discovery options to include self
xbee.atcmd("NO", 2)
xbee.atcmd("AC")
time.sleep(.5)
# Perform Network Discovery and print out the results
print ("Network Discovery in process...")
nodes = list(xbee.discover())
if nodes:
    for node in nodes:
    print("\nRadio discovered:")
    for key, value in node.items():
        print("\t{:<12} : {}".format(key, value))
# Set NO back to the default value
xbee.atcmd("NO", 0)
xbee.atcmd("AC")
