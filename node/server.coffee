express = require "express"
fs = require "fs"
imgproc = require "../cpp/build/Release/imgproc"

app = express()
app.use express.bodyParser({ keepExtensions: true })

app.get "/hello.txt", (req, res) -> res.send "Hello World!"
app.get "/images", (req, res) -> res.json { files: fs.readdirSync("./images") }
app.get "/opencvinfo", (req, res) -> res.send imgproc.buildInformation()

app.post "/barcode", (req, res) ->
    res.json { "barcode": imgproc.scanBarcode(req.files.file.path) }

app.post "/text", (req, res) ->
    res.json { "text": imgproc.scanText(req.files.file.path) }

app.post "/process", (req, res) ->
    console.log JSON.stringify(req.files)
    res.send req.files.file

app.listen 3000
console.log "Listening on port 3000"
