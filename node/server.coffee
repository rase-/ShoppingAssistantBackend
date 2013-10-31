express = require "express"
fs = require "fs"
cv = require "../cpp/build/Release/cv"

app = express()

app.get "/hello.txt", (req, res) -> res.send "Hello World!"
app.get "/images", (req, res) -> res.json { files: fs.readdirSync("./images") }
app.get "/opencvinfo", (req, res) -> res.send cv.buildInformation()
app.get "/process", (req, res) ->
    # Eventually replace toUpperCase call with the actual C/C++ module call
    results = file.toUpperCase() for file in fs.readdirSync("./images")
    res.json { results: results }

app.listen 3000
console.log "Listening on port 3000"
