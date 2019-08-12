import React, { useRef } from 'react';

import getUrlParam from '../../../shared/utils/getUrlParam';

const Form = ({ createQuestion, loading }) => {
  const nameInput = useRef('');
  const emailInput = useRef('');
  const subjectInput = useRef('');

  const handleSubmit = event => {
    event.preventDefault();

    createQuestion({
      variables: {
        agencyId: getUrlParam('agency_id'),
        authorName: nameInput.current.value,
        authorEmail: emailInput.current.value,
        subject: subjectInput.current.value,
        url: getUrlParam('url'),
      },
    });
  };

  const disableInputs = loading;

  return (
    <form onSubmit={handleSubmit}>
      <div className="question-form__input-wrapper question-form__input-wrapper--question">
        <label>Hvad vil du spørge om?</label>
        <div>
          <textarea disabled={disableInputs} rows="5" ref={subjectInput} />
        </div>
      </div>
      <div className="question-form__input-wrapper question-form__input-wrapper--name">
        <label>
          Dit navn
          <div>
            <input
              type="text"
              disabled={disableInputs}
              ref={nameInput}
              required={true}
            />
          </div>
        </label>
      </div>
      <div className="question-form__input-wrapper question-form__input-wrapper--email">
        <label>
          Din e-mail adresse
          <div>
            <input
              type="email"
              disabled={disableInputs}
              ref={emailInput}
              required={true}
            />
          </div>
        </label>
      </div>

      <input type="submit" value="Spørg nu" />
    </form>
  );
};

export default Form;
