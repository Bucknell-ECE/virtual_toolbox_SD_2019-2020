#!/usr/bin/env python3

from __future__ import print_function
import time
from datetime import datetime
import mercury
import csv
UIDList = []
reader = mercury.Reader("tmr:///dev/ttyUSB0", baudrate=115200)

def scanner():
	

	#print(reader.get_model())

    reader.set_region("NA2")
    reader.set_read_plan([1], "GEN2", read_power=1900)

    reader.start_reading(lambda tag: UIDList.append(tag.epc))

	
    time.sleep(1)
    #print(UIDList)
    reader.stop_reading()
    return(UIDList)
    


if __name__ == "__main__":
    UIDList = scanner()
    #str1 = ''.join(str(x) for x in listIDs)
    
    stringlist = []
    for elem in UIDList:
        sp = elem.decode("utf-8")
        stringlist.append(sp)


    with open('uid.csv', 'w') as f:
        filewriter = csv.writer(f)
        filewriter.writerow(stringlist)

