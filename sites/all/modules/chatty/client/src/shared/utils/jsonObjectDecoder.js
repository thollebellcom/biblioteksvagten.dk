const JSONObjectDecoder = json => {
  let result = [];
  const keys = Object.keys(json);

  keys.forEach(function(key) {
    result.push(json[key]);
  });

  return result;
};

export default JSONObjectDecoder;
