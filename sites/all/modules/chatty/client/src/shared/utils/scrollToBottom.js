const scrollToBottom = element => {
  if (element.length === 0) {
    return false;
  }

  const { scrollHeight } = element;

  element.scrollTop = scrollHeight;
}

export default scrollToBottom;
