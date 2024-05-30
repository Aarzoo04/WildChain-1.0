const express = require('express');
const path = require('path');
const bcrypt = require('bcrypt');
const crypto = require('crypto');
const multer = require('multer');
const fs = require('fs')
const {User, Tiger} = require("./config");

const saltRounds = 10;

const app = express();
//Convert data to json
app.use('/uploads', express.static(path.join(__dirname, '..', 'uploads')));
app.use(express.json());
app.use(express.urlencoded({extended: false}));

// Set EJS as view engine
app.set('view engine','ejs');
//Static file
app.use(express.static("public"));

app.get("/",(req,res)=>{
    res.render("login");
});

app.get("/signup", (req, res) => {
    res.render("signup");
});

app.post("/signup", async (req, res) => {
    const data = {
        name: req.body.username,
        password: req.body.password
    };

    // Check if the username already exists in the database
    const existingUser = await User.findOne({ name: data.name });

    if (existingUser) {
        res.send('User already exists. Please choose a different username.');
        return;
    }
    else{
        // Hash the password using bcrypt
        
        const hashedPassword = await bcrypt.hash(data.password, saltRounds);
        data.password = hashedPassword

        // Insert the user data into the User
        const userdata = await User.insertMany(data);
        console.log(userdata);
        res.send('User registered successfully.');
    }
        
      
});


// Login User
app.post("/login",async(req,res)=>{

    try{
        const  check = await User.findOne({name:req.body.username});
        console.log(check);
        if(!check){
            res.send("User Name Cannot Found");
        }
        //compare hashed password
        const isPasswordMatch = await bcrypt.compare(req.body.password,check.password);
        console.log(isPasswordMatch);
        if(isPasswordMatch){
            // res.status(200).json({message: "Logged in successfully"});
            res.render("home");
        }
        else{
            res.send("Wrong Password");
        }
    }catch{
        res.send("Wrong Details");
    }
});

app.get("/update", (req, res) => {
    res.render("update");
});

const storage = multer.diskStorage({
    destination: function(req, file, cb) {
        cb(null, 'uploads/');
    },
    filename: function(req, file, cb) {
        cb(null, Date.now() + '-' + file.originalname);
    }
});
const upload = multer({ storage: storage });

// POST route to update tiger details
app.post('/update', upload.single('image'), async (req, res) => {
    try {
        const { tiger_id, location } = req.body;
        // Find tiger by tiger_id
        const tiger = await Tiger.findOne({ tiger_id: tiger_id });
        if (!tiger) {
            return res.status(404).json({ error: 'Tiger not found' });
        }

        // Update tiger details
        if (req.file) {
            tiger.image = req.file.filename;
        }
        
        tiger.timestamp = new Date(); // Set current date and time

        if (location) {
            tiger.location = location
        }

        // Save updated tiger
        await tiger.save();

        res.status(200).json({ message: 'Tiger details updated successfully', tiger });

        const updatedTiger = await Tiger.findOne( {tiger_id: tiger_id});
        const updatedTigerToString = JSON.stringify(tiger);
        const hashedDataOfTiger = crypto.createHash('sha256').update(updatedTigerToString).digest('hex');
        // Write hashed data to a .txt file
        fs.writeFileSync("hash.txt", hashedDataOfTiger);

    }  catch (error) {
        // console.error(error);
        res.status(500).send('Internal server error' );
    }
});

app.get("/view", (req, res) => {
    res.render("view");
});

app.post("/view", async (req, res) => {
    try {
        // Extract the tiger_id from the request body
        const { tiger_id } = req.body;

        // Find tiger by tiger_id in the MongoDB database
        const tiger = await Tiger.findOne({ tiger_id: tiger_id });
        if (!tiger) {
            return res.send("Tiger not found");
        }
        console.log("Retrieved Tiger Data:", tiger.image);
        res.render("view", { tiger: tiger });
        console.log({ tiger: tiger })
    } catch (error) {
        console.error(error);
        res.status(500).send('Internal server error');
    }
});


const port = 5000;
app.listen(port,()=>{
    console.log(`Server running on Port: ${port}`);
})