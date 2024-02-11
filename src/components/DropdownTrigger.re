open Flag;
open Svg;
open SharedStyles;
open Types;

module type DropdownTrigger = {
  [@react.component]
  let make:
    (
      ~selectedOption: option(Types.country),
      ~onClick: ReactEvent.Mouse.t => unit,
      ~innerRef: ReactDOM.domRef
    ) =>
    React.element;
};
module DropdownTrigger: DropdownTrigger = {
  module DropdownTriggerIcon = {
    module Styles = {
      let container =
        ReactDOM.Style.make(
          ~height="8px",
          ~width="8px",
          ~display="flex",
          ~alignItems="center",
          (),
        );
    };
    [@react.component]
    let make = () =>
      <div style=Styles.container>
        <Svg width="8" height="8" viewBox="0 0 8 8">
          <path
            d="M0 2H8L4 7L0 2Z"
            fill="#333333"
            fillRule="evenodd"
            clipRule="evenodd"
          />
        </Svg>
      </div>;
  };
  module Styles = {
    let button =
      SharedStyles.makeStyleWithTextPrimary(
        ~height="26px",
        ~padding="4px 10px",
        ~display="flex",
        ~alignItems="center",
        ~backgroundColor=SharedStyles.Colors.background,
        ~borderColor=SharedStyles.Colors.borderDark,
        ~borderWidth="1px",
        ~borderStyle="solid",
        ~borderRadius="3px",
        ~cursor="pointer",
        ~width="140px",
        (),
      );
    let container =
      ReactDOM.Style.make(
        ~display="flex",
        ~alignItems="center",
        ~justifyContent="space-between",
        ~width="100%",
        (),
      );
    let selectedCountry =
      ReactDOM.Style.make(~display="flex", ~alignItems="center", ());
    let triggerIcon = ReactDOM.Style.make(~marginLeft="6px", ());
    let label =
      ReactDOM.Style.make(
        ~height="18px",
        ~lineHeight="20px",
        ~textOverflow="ellipsis",
        ~whiteSpace="nowrap",
        ~maxWidth="79px",
        ~overflow="hidden",
        (),
      );
  };
  [@react.component]
  let make = (~selectedOption: option(Types.country), ~onClick, ~innerRef) => {
    let (flag, label) =
      switch (selectedOption) {
      | Some({value, label, _}) => (
          <Flag countryCode=value />,
          <div style=Styles.label> {React.string(label)} </div>,
        )
      | None => (
          React.null,
          <div style={ReactDOM.Style.make(~lineHeight="20px", ())}>
            {React.string("Select a country")}
          </div>,
        )
      };

    <button ref=innerRef style=Styles.button onClick>
      <div style=Styles.container>
        <div style=Styles.selectedCountry> flag label </div>
        <div style=Styles.triggerIcon> <DropdownTriggerIcon /> </div>
      </div>
    </button>;
  };
};
