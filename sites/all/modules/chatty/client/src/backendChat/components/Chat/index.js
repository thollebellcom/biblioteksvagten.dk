import './index.css';
import React, { useContext } from 'react';
import { Mutation, Query } from 'react-apollo';

import GET_QUESTION_QUERY from '../../../shared/Apollo/query/getQuestion';
import CREATE_MESSAGE_MUTATION from '../../../shared/Apollo/mutation/createMessage';
import { ChatContext, RESET_CHAT } from '../../context/ChatContext';

import Bar from './Bar';
import MessageList from './MessageList';
import Actions from './actions';
import Form from './Form';

const ChatContainer = () => {
  const [state, dispatch] = useContext(ChatContext);

  return (
    <Query
      query={GET_QUESTION_QUERY}
      fetchPolicy="network-only"
      variables={{
        questionId: state.backendChat.questionId,
      }}
    >
      {({ data, loading, subscribeToMore }) => {
        if (!data || !data.question || loading) return '';

        // The received question is marked as complete, so dispatch an action
        // invalidating everything in the state.
        if (data.question.status === 'complete') {
          dispatch({
            type: RESET_CHAT,
            payload: null,
          });
        }

        return (
          <div className="backend-chat">
            <Bar title={data.question.authorName} />
            <MessageList
              subject={data.question.subject}
              questionCreatedAt={data.question.createdAt}
              messages={data.question.messages}
              subscribeToMore={subscribeToMore}
            />

            <Actions />

            <Mutation mutation={CREATE_MESSAGE_MUTATION}>
              {createMessage => <Form createMessage={createMessage} />}
            </Mutation>
          </div>
        );
      }}
    </Query>
  );
};
export default ChatContainer;
