const express = require("express");
const cors = require("cors");
const { Connection, Request } = require("tedious");
const app = express();
app.use(cors());
const port = 3000;
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

// Attempt to connect and execute queries if connection goes through
connection.on("connect", (err) => {
  if (err) {
    console.error(err.message);
  } else {
    queryDatabase();
  }
});

connection.connect();

app.get("/", (req, res) => {
  //res.send('Hello World!')
  res.json({ hello: ["world", "test "], bye: "mom", hi: "dad" });
});

app.get("/sql", (req, res) => {
  res.send(queryDatabase());
});

// TODO: Add endpoint for inserting data using POST request

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});
