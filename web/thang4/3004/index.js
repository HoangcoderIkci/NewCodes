const express = require('express')
const app = express()
const port = 3000;
const mongoose = require('mongoose');
mongoose.connect('mongodb://127.0.0.1:27017/products-test');

const Product = mongoose.model('Product',{
  title: String,
  price: Number,
  thumbnail: String
});



app.set('views', './views')
app.set('view engine', 'pug')

app.use(express.static('public'))

app.get('/', (req, res) => {
  res.render('index', { titlePage: 'Hey', message: 'Hello trang chủ' })
})

app.get('/contact', (req, res) => {
  res.render('contact', { titlePage: 'Hey', message: 'Contact' })
})

app.get('/products',async (req, res) => {
  const products = await Product.find({})
  //console.log(products)
  res.render('products', {
    titlePage: 'List Products',
    products: products
  })
  res.send("List Products")
})

app.listen(port)