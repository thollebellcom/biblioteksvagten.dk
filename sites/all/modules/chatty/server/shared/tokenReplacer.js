const tokenReplacer = (string, settings) =>
  string.replace(settings.token, settings.replaceBy);

module.exports = tokenReplacer;
