function decodeUplink(input) {
  var data = input.bytes;
  
  var json = {
    datalogger: data[0],
    battery_level: data[1],
    temperature: {
      temperature_s1: data[2],
      temperature_s2: data[3],
      temperature_s3: data[4]
    },
    humidity: {
      humidity_s1: data[5],
      humidity_s2: data[6],
      humidity_s3: data[7]
    }
  }

  return {
    data: json,
    warnings: [],
    errors: []
  };
}