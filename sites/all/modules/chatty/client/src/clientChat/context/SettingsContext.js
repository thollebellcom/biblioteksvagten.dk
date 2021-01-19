import React, { useReducer, useEffect } from 'react';

export const RESET_SETTINGS = 'RESET_SETTINGS';
export const SET_SETTINGS = 'SET_SETTINGS';

export const SettingsContext = React.createContext();

export const SettingsReducer = (state, action) => {
  switch (action.type) {
    case RESET_SETTINGS:
      localStorage.removeItem('clientSettings');

      return {};
    case SET_SETTINGS:
      localStorage.setItem('clientSettings', JSON.stringify(action.payload));

      return {
        ...action.payload,
        messages: JSON.parse(action.payload.messages),
        standardAnswers: JSON.parse(action.payload.standardAnswers),
      };
    default:
      return state;
  }
};

export const SettingsProvider = ({ children }) => {
  const [state, dispatch] = useReducer(SettingsReducer, {});

  // Grab data from localStorage on first run.
  // eslint-disable-next-line
  useEffect(() => {
    const localStorageData = localStorage.getItem('clientSettings');

    if (localStorageData) {
      dispatch({
        type: SET_SETTINGS,
        payload: JSON.parse(localStorageData),
      });
    }
  }, []);

  return (
    <SettingsContext.Provider value={[state, dispatch]}>
      {children}
    </SettingsContext.Provider>
  );
};
