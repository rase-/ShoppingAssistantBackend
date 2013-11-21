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
couchdb.exists (err, exists) ->
    if err
        console.log "Error: #{err}"
    else if exists
        console.log "CouchDB database found"
    else
        console.log "CouchDB database not found, creating..."
        db.create()

# Routes and actions
## User actions
app.get "/products/:name", (req, res) ->
    productName = req.params.name
    couchdb.get productName, (err, data) ->
        res.json data

app.post "/products", (req, res) ->
    product = req.body # check that this actually contains the product info
    barcodeImgPath = req.files.barcode.path
    textImgPath = [] # Here actually select those that have text in their name
    logoImgPath = req.files.logo.path
    product["barcode"] = imgproc.scanBarcode barcodeImgPath if barcodeImgPath
    # Here copy the logo img to correct place and set path, make then name
    # product name, also check that it doesn't exist
    product["bagOfWords"] = []
    # Loop through all images and scan text, add to BoW

    couchdb.save product.name, product, (err, res) -> console.log "Error saving product"
    # Save to redis with barcode as key
    # Modify either redis or couchdb stored global term array for tf-idf

app.post "/products/match", (req, res) ->
    console.log JSON.stringify(req.files)
    barcode = imgproc.scanBarcode req.files.file.path
    text = imgproc.scanText req.files.file.path
    # Here filter out those IDs with close enough freak logos
    # Here filter out with text
    # Here filter out with SURF

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

# Start the app
app.listen 3000
console.log "Listening on port 3000"
