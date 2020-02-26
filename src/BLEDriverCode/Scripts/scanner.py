import bluetoothctl


def scan():
	#return string of all tags found


	if __name__ == "__main__":

		print("Init bluetooth...")
		print("Ready!")
		bluetoothctl.start_scan()
		print("Scanning for 10 seconds...")
		for i in range(0, 10):
			print(i)
			time.sleep(1)
		vect = bluetoothctl.get_discoverable_devices()
		
		return(vect)
	return(0)
