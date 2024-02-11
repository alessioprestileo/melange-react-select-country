module Blanket = {
  module Styles = {
    let container =
      ReactDOM.Style.make(
        ~bottom="0",
        ~left="0",
        ~top="0",
        ~right="0",
        ~position="fixed",
        ~zIndex="1",
        (),
      );
  };
  [@react.component]
  let make = (~onClick: _ => unit) => <div style=Styles.container onClick />;
};
