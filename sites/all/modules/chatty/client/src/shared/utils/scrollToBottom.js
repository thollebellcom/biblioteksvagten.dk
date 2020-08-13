const scrollToBottom = element => {
  if (!element) {
    return false;
  }

  const { scrollHeight } = element;

  element.scrollTop = scrollHeight;
}

export default scrollToBottom;
