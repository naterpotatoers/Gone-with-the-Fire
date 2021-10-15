const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  //res.send('Hello World!')
  res.json({"hello": ["world", "test "], "bye": "mom", "hi": "dad"})
})
app.get('/hello/', (req, res) => {
    res.send('Hello Garrett!')
  })
  app.get('/hello/test', (req, res) => {
    res.send('Hello Garrett! whats up')
  })

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})