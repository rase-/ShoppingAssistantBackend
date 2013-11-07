# just give as parameter the file name you wish to send to the running server
# when scanning barcodes
curl -i -F file=@$1 http://localhost:3000/scan
