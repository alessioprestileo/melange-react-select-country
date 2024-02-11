open Blanket;

module type Dropdown = {
  [@react.component]
  let make:
    (
      ~className: string,
      ~onClose: unit => unit,
      ~isOpen: bool,
      ~trigger: React.element,
      ~children: React.element
    ) =>
    React.element;
};

module Dropdown: Dropdown = {
  module Styles = {
    let container = ReactDOM.Style.make(~position="relative", ());
  };
  [@react.component]
  let make = (~className, ~onClose, ~isOpen, ~trigger, ~children) => {
    let handleKeyDown = (event: ReactEvent.Keyboard.t): unit =>
      if (ReactEvent.Keyboard.key(event) === "Escape") {
        onClose();
      };

    <div className style=Styles.container onKeyDown=handleKeyDown>
      trigger
      {isOpen
         ? <React.Fragment>
             children
             <Blanket onClick=onClose />
           </React.Fragment>
         : React.null}
    </div>;
  };
};
