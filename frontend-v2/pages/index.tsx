import React from "react";
import { Line } from "react-chartjs-2";

function createGraph(data: any, label: string, dates: any) {
  const graphInfo = {
    labels: dates,
    datasets: [
      {
        label: label,
        fill: false,
        lineTension: 0.1,
        backgroundColor: "rgba(75,192,192,0.4)",
        borderColor: "rgba(75,192,192,1)",
        borderCapStyle: "butt",
        borderDash: [],
        borderDashOffset: 0.0,
        borderJoinStyle: "miter",
        pointBorderColor: "rgba(75,192,192,1)",
        pointBackgroundColor: "#fff",
        pointBorderWidth: 1,
        pointHoverRadius: 5,
        pointHoverBackgroundColor: "rgba(75,192,192,1)",
        pointHoverBorderColor: "rgba(220,220,220,1)",
        pointHoverBorderWidth: 2,
        pointRadius: 1,
        pointHitRadius: 10,
        data: data,
      },
    ],
  };
  return graphInfo;
}

export async function getStaticProps() {
  const res = await fetch("http://localhost:5000/iot");
  const posts = await res.json();
  // console.log(posts);
  return {
    props: {
      posts,
    },
  };
}

function Index({ posts }) {
  let temp = posts.map((item) => {
    return item.temperature;
  });
  let humid = posts.map((item) => {
    return item.humidity;
  });
  let long = posts.map((item) => {
    return item.longitude;
  });
  let lati = posts.map((item) => {
    return item.latitude;
  });
  let smoke = posts.map((item) => {
    return item.smoke;
  });
  let dates = posts.map((item) => {
    return item.date;
  });
  return (
    <div>
      <h2>Temperature</h2>
      <Line
        data={createGraph(temp, "Temperature", dates)}
        width={400}
        height={200}
      />
      <h2>Humidity</h2>
      <Line
        data={createGraph(humid, "Humidity", dates)}
        width={400}
        height={200}
      />
      <h2>Longitude</h2>
      <Line
        data={createGraph(long, "Longitude", dates)}
        width={400}
        height={200}
      />
      <h2>Latitude</h2>
      <Line
        data={createGraph(lati, "Latitude", dates)}
        width={400}
        height={200}
      />
      <h2>Smoke</h2>
      <Line
        data={createGraph(smoke, "Smoke", dates)}
        width={400}
        height={200}
      />
    </div>
  );
}

export default Index;
