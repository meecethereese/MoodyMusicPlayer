var requestOptions = {
  method: 'GET',
  redirect: 'follow'
};

fetch("http://shellhacksesp.local/sad", requestOptions)
  .then(response => response.text())
  .then(result => console.log(result))
  .catch(error => console.log('error', error));
