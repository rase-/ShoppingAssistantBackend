# External modules
express = require "express"
cradle = require "cradle"
redis = require "redis"
fs = require "fs"
imgproc = require "../cpp/build/Release/imgproc"

# Initialize app
app = express()
app.use express.bodyParser({ keepExtensions: true })

# Initialize DBs
couchdb = new (cradle.Connection)().database "products"
redisdb = redis.createClient() # This function actutally takes the id of the db as argument, 0 by default

# Routes and actions
## User actions
app.get "products/:id", (req, res) ->
    productId = req.params.id
    couchdb.get productId, (err, data) ->
        res.json JSON.stringify(data)

## Useful checks
app.get "/hello.txt", (req, res) -> res.send "Hello World!"
app.get "/images", (req, res) -> res.json { files: fs.readdirSync("./images") }
app.get "/opencvinfo", (req, res) -> res.send imgproc.buildInformation()

## Image processing
app.post "/barcode", (req, res) ->
    res.json { "barcode": imgproc.scanBarcode(req.files.file.path) }

app.post "/text", (req, res) ->
    res.json { "text": imgproc.scanText(req.files.file.path) }

app.post "/logo", (req, res) ->
    res.json { "score": imgproc.matchLogos(req.files.file.path, req.files.file.path) }

app.post "/process", (req, res) ->
    console.log JSON.stringify(req.files)
    res.send req.files.file

# Start the app
app.listen 3000
console.log "Listening on port 3000"
