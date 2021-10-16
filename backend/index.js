const express = require("express");
const cors = require("cors");
const { Connection, Request } = require("tedious");
const { json } = require("express");
const app = express();
app.use(cors());
app.use(express.json({ limit: "2mb" }));
app.use(express.urlencoded({ extended: false }));
const port = 5000;
const config = {
  authentication: {
    options: {
      userName: "gone-with-the-fire-user", // update me
      password: "TiconderogaHB#2", // update me
    },
    type: "default",
  },
  server: "gone-with-the-fire-db.database.windows.net", // update me
  options: {
    database: "gone-with-the-fire-db", //update me
    encrypt: true,
  },
};
const connection = new Connection(config);

function queryDatabase() {
  console.log("Reading rows from the Table...");

  // Read all rows from table
  const request = new Request(
    `SELECT * FROM basic_example_table;`,
    (err, rowCount) => {
      if (err) {
        console.error(err.message);
      } else {
        console.log(`${rowCount} row(s) returned`);
      }
    }
  );

  request.on("row", (columns) => {
    columns.forEach((column) => {
      console.log("%s\t%s", column.metadata.colName, column.value);
    });
  });

  connection.execSql(request);
}

connection.connect();

app.get("/", (req, res) => {
  res.send("Hello World!");
});

app.get("/sql", (req, res) => {
  res.send(queryDatabase());
});

app.post("/", (req, res) => {
  console.log(req.body);
  res.jsonp(res.body);
});

// TODO: Add endpoint for inserting data using POST request

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});
