const getUrlParams = name => {
  // eslint-disable-next-line no-useless-escape
  name = name.replace(/[\[]/, '\\[').replace(/[\]]/, '\\]');

  const regex = new RegExp('[\\?&]' + name + '=([^&#]*)');
  // eslint-disable-next-line no-restricted-globals
  const results = regex.exec(location.search);

  return results === null
    ? ''
    : decodeURIComponent(results[1].replace(/\+/g, ' '));
};

export default getUrlParams;
