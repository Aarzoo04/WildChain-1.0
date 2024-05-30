const mongoose=require('mongoose');
const connect=mongoose.connect("mongodb+srv://Aarzoo04:Saini2535@wildchain.q3uv5g8.mongodb.net/Authentication");

// Check database connected or not
connect.then(()=>{
    console.log("Database connected successfully");
})
.catch(()=>{
    console.log("Database cannot be connected");
})

//Create Schema

const LoginSchema = new mongoose.Schema({
    name:{
        type: String,
        required: true
    },
    password:{
        type:String,
        required: true
    }
});


// Create collection
const User = new mongoose.model("Users", LoginSchema);

const TigerSchema = new mongoose.Schema({
    
        tiger_id: String,
        image: String,
        timestamp: Date,
        location: String
})

const Tiger = new mongoose.model("TigerDetails", TigerSchema);

module.exports = { User, Tiger };






