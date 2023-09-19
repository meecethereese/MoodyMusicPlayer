var requestOptions = {
  method: 'GET',
  redirect: 'follow'
};

fetch("http://shellhacksesp.local/angry", requestOptions)
  .then(response => response.text())
  .then(result => console.log(result))
  .catch(error => console.log('error', error));
