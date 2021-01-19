import differenceInSeconds from 'date-fns/difference_in_seconds';
import convertTimestampToDate from './convertTimestampToDate';

const calculateOffline = timestamp => {
  const distanceInSeconds = 15;
  const date = convertTimestampToDate(timestamp);

  // Difference is bigger than $distance. It is seen as offline.
  if (differenceInSeconds(new Date(), date) > distanceInSeconds) {
    return true;
  }

  return false;
};

export default calculateOffline;
