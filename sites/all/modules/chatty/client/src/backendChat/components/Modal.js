import React from 'react';

const Modal = ({ children, title, toggle, visible }) => {
  return (
    <div className={`overlay ${visible ? 'overlay--visible' : ''}`}>
      <div className="modal">
        <div className="modal__heading">
          <h1 className="modal__heading__title">{title}</h1>
        </div>
        <div className="modal__body">{children}</div>
        <div className="modal__footer">
          <button
            className="modal__footer__button"
            onClick={() => toggle(!visible)}
          >
            Luk vindue
          </button>
        </div>
      </div>
    </div>
  );
};

export default Modal;
