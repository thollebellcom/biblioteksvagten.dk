import daLocale from 'date-fns/locale/da';
import distanceInWordsToNow from 'date-fns/distance_in_words_to_now';

const generateDateString = date => {
  const mutatedDate = distanceInWordsToNow(date, {
    locale: daLocale,
  });

  return `For ${mutatedDate} siden`;
};

export default generateDateString;
