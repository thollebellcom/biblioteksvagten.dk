import daLocale from 'date-fns/locale/da';
import format from 'date-fns/format';

const generateDateString = date => {
  const mutatedDate = format(date, 'DD.MM.YYYY', {
    locale: daLocale,
  });

  const mutatedTime = format(date, 'HH:mm', {
    locale: daLocale,
  });

  return `D. ${mutatedDate} kl. ${mutatedTime}`;
};

export default generateDateString;
