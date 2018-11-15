import bluetooth as bt
import sys, time


def sendMessage(sock):
    m = raw_input("Enter a value between -1 and 9 to send: ")
    try:
        msg = int(m)
        if msg not in range(-1,10):
            raise ValueError("This int is not in the range we asked for")

    except Exception as e:
        print "Please enter an integer between 0-9 inclusive.\nEnter -1 to quit"

    if msg != -1: sock.send(str(msg))
    else:         return -1



def main():
    port = 1
    HC05 = "98:D3:32:11:67:C2"

    nearDevices = bt.discover_devices()
    s = bt.BluetoothSocket(bt.RFCOMM)

    s.connect((HC05, port))
    print "Successfully connected to HC05!"

    while True:
        x = sendMessage(s)
        if x == -1: break

    s.close()
    print "Successfully disconected from HC05!"


if __name__ == "__main__":
    main()
