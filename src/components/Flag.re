module type Flag = {
  [@react.component]
  let make: (~countryCode: string) => React.element;
};
module Flag: Flag = {
  module Styles = {
    let flagContainer = ReactDOM.Style.make(~marginRight="8px", ());
    let flag = ReactDOM.Style.make(~width="14px", ());
  };
  [@react.component]
  let make = (~countryCode) => {
    let className = "fi fi-" ++ countryCode;
    <div style=Styles.flagContainer>
      <span style=Styles.flag className />
    </div>;
  };
};
