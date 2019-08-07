import './index.css';
import React, { useContext } from 'react';
import { Mutation, Query } from 'react-apollo';

import { ChatContext } from '../../context/ChatContext';
import GET_QUESTION_QUERY from '../../../shared/Apollo/query/getQuestion';
import CREATE_MESSAGE_MUTATION from '../../../shared/Apollo/mutation/createMessage';
import { RESET_CHAT } from '../../../backendChat/context/ChatContext';
import MAKE_HEARTBEAT_MUTATION from '../../../shared/Apollo/mutation/makeHeartbeat';

import StatusBar from './StatusBar';
import MessageList from './MessageList';
import Form from './Form';

const ChatContainer = () => {
  const [state, dispatch] = useContext(ChatContext);

  return (
    <Query
      query={GET_QUESTION_QUERY}
      variables={{
        questionId: state.clientChat.questionId,
      }}
    >
      {({ data, loading, subscribeToMore }) => {
        if (!data || loading) return '';

        const { status } = data.question;
        const disabledStates = status === 'pending' || status === 'complete';

        // The recieved question is marked as complete, so dispatch an action
        // invalidating everything in the state.
        if (data.question.status === 'complete') {
          dispatch({
            type: RESET_CHAT,
            payload: null,
          });
        }

        return (
          <div className="client-chat">
            <StatusBar status={data.question.status} />

            <Mutation mutation={MAKE_HEARTBEAT_MUTATION}>
              {makeHeartbeat => (
                <MessageList
                  disabled={disabledStates}
                  subject={data.question.subject}
                  questionCreatedAt={data.question.createdAt}
                  messages={data.question.messages}
                  subscribeToMore={subscribeToMore}
                  makeHeartbeat={makeHeartbeat}
                />
              )}
            </Mutation>

            <Mutation mutation={CREATE_MESSAGE_MUTATION}>
              {createMessage => (
                <Form disabled={disabledStates} createMessage={createMessage} />
              )}
            </Mutation>
          </div>
        );
      }}
    </Query>
  );
};
export default ChatContainer;
