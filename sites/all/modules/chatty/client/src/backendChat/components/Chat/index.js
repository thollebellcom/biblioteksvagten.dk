import './index.css';
import React, { useContext } from 'react';
import { Mutation, Query } from 'react-apollo';

import GET_QUESTION_QUERY from '../../../shared/Apollo/query/getQuestion';
import GET_MESSAGES_QUERY from '../../../shared/Apollo/query/getMessages';
import CREATE_MESSAGE_MUTATION from '../../../shared/Apollo/mutation/createMessage';
import { ChatContext, RESET_CHAT } from '../../context/ChatContext';

import OfflineMessage from './OfflineMessage';
import ReadonlyMessage from './ReadonlyMessage';
import Bar from './Bar';
import MessageList from './MessageList';
import Actions from './actions';
import Form from './Form';

const ChatContainer = () => {
  const myConsultantId =
    window.Drupal &&
    window.Drupal.settings &&
    window.Drupal.settings.consultantId
      ? window.Drupal.settings.consultantId.toString()
      : '1';
  const [state, dispatch] = useContext(ChatContext);

  return (
    <Query
      query={GET_QUESTION_QUERY}
      variables={{
        questionId: state.backendChat.questionId,
      }}
    >
      {({ data: {question}, loading, subscribeToMore }) => {
        if (!question || loading) return '';

        // The received question is marked as complete, so dispatch an action
        // invalidating everything in the state.
        if (question.status === 'complete') {
          dispatch({
            type: RESET_CHAT,
            payload: null,
          });
        }

        return (
          <div className="backend-chat">
            <Bar name={question.authorName} email={question.authorEmail} source={question.source} />

            <OfflineMessage lastHeartbeat={question.lastHeartbeatAt} />

            {question.consultant !== myConsultantId && <ReadonlyMessage />}

            <Query 
              query={GET_MESSAGES_QUERY}
              variables={{ questionId: state.backendChat.questionId }}
              fetchPolicy="network-only"
              pollInterval={2000}
            >
              {({ data: { messages }, loading }) => {
                if (!messages) return null;

                return (
                  <MessageList
                    author={question.authorName}
                    subject={question.subject}
                    questionCreatedAt={question.createdAt}
                    messages={messages}
                  />
                );
              }}
            </Query>

            {question.consultant === myConsultantId && (
              <Mutation mutation={CREATE_MESSAGE_MUTATION} id={question.id}>
                {createMessage => <Form questionId={question.id} createMessage={createMessage} />}
              </Mutation>
            )}
          </div>
        );
      }}
    </Query>
  );
};
export default ChatContainer;
