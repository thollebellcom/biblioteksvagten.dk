import './index.css';
import React, { useContext } from 'react';
import { Mutation } from 'react-apollo';

import CREATE_QUESTION_MUTATION from '../../../shared/Apollo/mutation/createQuestion';
import { ChatContext, SET_ACTIVE_CHAT } from '../../context/ChatContext';

import Form from './Form';

const CreateQuestion = () => {
  const [, dispatch] = useContext(ChatContext);

  return (
    <div className="question-form">
      <Mutation mutation={CREATE_QUESTION_MUTATION}>
        {(createQuestion, { loading, data }) => {
          if (data && data.createQuestion.id) {
            dispatch({
              type: SET_ACTIVE_CHAT,
              payload: data.createQuestion.id,
            });
          }

          return <Form createQuestion={createQuestion} loading={loading} />;
        }}
      </Mutation>
    </div>
  );
};

export default CreateQuestion;
