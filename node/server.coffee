# Thresholds
Threshold = { "FREAK": 0.5 }

# External modules
express = require "express"
cradle = require "cradle"
redis = require "redis"
fs = require "fs-extra"
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
        couchdb.create()
        db.save "_design/products", {all: { map: (doc) -> emit doc.name, doc if doc.name }}
        console.log "...Created!"

# Useful piece of code, do not destroy yet
# couchdb.view "products/all", (err, result) ->
#         result.forEach (key, row, id) ->
#             keys.push key
# 

# Routes and actions
## User actions
app.get "/products/:name", (req, res) ->
    productName = req.params.name
    couchdb.get productName, (err, data) ->
        res.json data

app.post "/products", (req, res) ->
    # Initialize product and paths
    product = JSON.parse req.body.product
    res.send {"status": "No images uploaded"} unless req.files
    barcodeImgPath = req.files.barcode.path if req.files.barcode
    textImgPaths = (info.path for file, info of req.files when file.indexOf("text") >= 0)
    console.log JSON.stringify(textImgPaths)
    logoImgPath = req.files.logo.path if req.files.logo

    product["barcode"] = imgproc.scanBarcode barcodeImgPath if barcodeImgPath

    # Copy logo image
    if logoImgPath
        fs.copy logoImgPath, "./images/#{product.name}.jpg", (err) ->
            return console.error(err) if err
            console.log "Copied logo" 

    # Build bag of words
    product["bagOfWords"] = {}
    texts = (imgproc.scanText(file) for file in textImgPaths)
    for text in texts
        tokens = text.split(" ")
        words = for token in tokens
            token.replace /\W/g, ''
        words = (word for word in words when word.length > 0)
        for word in words
            product["bagOfWords"][word] = 0 unless product["bagOfWords"][word]
            product["bagOfWords"][word]++
   
    # DB handling
    couchdb.save product.name, product, (err, res) -> 
        if err
            console.log "Error saving product: #{err}"
        else
            console.log "Saved product"

    res.json product
    # TODO: Save to redis with barcode as key
    # TODO: Modify either redis or couchdb stored global term array for tf-idf

app.post "/products/match", (req, res) ->
    barcode = imgproc.scanBarcode req.files.file.path
    text = imgproc.scanText req.files.file.path
    imgs = (file for file in fs.readdirSync("./images/") when file.indexOf("jpg") >= 0)
    freakResults = for img in imgs
        console.log "Matching with ./images/#{img}"
        match = imgproc.matchLogos(req.files.file.path, "./images/#{img}")
        { "img": img, "match": match }
    freakResultsFiltered = (freakResult for freakResult in freakResults when freakResult.match > Threshold.FREAK)
    res.json { results: freakResults, filtered: freakResultsFiltered }
    # Here filter out with text:
    ## Fetch database entries with img name
    ## Filter based on to threshold
    # Here filter out with SURF
    ## only for the filtered

## Useful checks
app.get "/hello.txt", (req, res) -> res.send "Hello World!"
app.get "/images", (req, res) -> res.json {"imgs":  (file for file in fs.readdirSync("./images") when file.indexOf("jpg") >= 0) }
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
