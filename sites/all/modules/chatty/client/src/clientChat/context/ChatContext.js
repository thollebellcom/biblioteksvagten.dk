import React, { useReducer, useEffect } from 'react';

export const RESET_CHAT = 'RESET_CHAT';
export const SET_ACTIVE_CHAT = 'SET_ACTIVE_CHAT';

export const ChatContext = React.createContext();

export const ChatReducer = (state, action) => {
  switch (action.type) {
    case RESET_CHAT:
      localStorage.removeItem('clientActiveQuestionId');

      return {
        ...state,
        clientChat: null,
      };
    case SET_ACTIVE_CHAT:
      localStorage.setItem('clientActiveQuestionId', action.payload);

      return {
        ...state,
        clientChat: {
          questionId: action.payload,
        },
      };
    default:
      return state;
  }
};

export const ChatProvider = ({ children }) => {
  const [state, dispatch] = useReducer(ChatReducer, {
    clientChat: null,
  });

  useEffect(() => {
    const data = localStorage.getItem('clientActiveQuestionId');

    if (data) {
      dispatch({
        type: SET_ACTIVE_CHAT,
        payload: data,
      });
    }
  }, []);

  return (
    <ChatContext.Provider value={[state, dispatch]}>
      {children}
    </ChatContext.Provider>
  );
};
