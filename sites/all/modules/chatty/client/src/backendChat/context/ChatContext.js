import React, { useReducer, useEffect } from 'react';

export const RESET_CHAT = 'RESET_CHAT';
export const SET_ACTIVE_CHAT = 'SET_ACTIVE_CHAT';
export const SET_CHAT_MESSAGE_TEXT = 'SET_CHAT_MESSAGE_TEXT';

export const ChatContext = React.createContext();

export const ChatReducer = (state, action) => {
  switch (action.type) {
    case RESET_CHAT:
      localStorage.removeItem('backendActiveQuestionId');

      return {
        ...state,
        backendChat: null,
      };
    case SET_ACTIVE_CHAT:
      localStorage.setItem('backendActiveQuestionId', action.payload);

      return {
        ...state,
        backendChat: {
          questionId: action.payload,
          message: '',
        },
      };
    case SET_CHAT_MESSAGE_TEXT:
      return {
        ...state,
        backendChat: {
          ...state.backendChat,
          message: action.payload,
        },
      };
    default:
      return state;
  }
};

export const ChatProvider = ({ children }) => {
  const [state, dispatch] = useReducer(ChatReducer, {
    backendChat: null,
  });

  // eslint-disable-next-line
  useEffect(() => {
    const data = localStorage.getItem('backendActiveQuestionId');

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
