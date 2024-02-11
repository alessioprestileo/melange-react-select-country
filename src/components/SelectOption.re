open Flag;
open ReactSelect;
open SharedStyles;
open Spread;

module type SelectOption = {
  let render: ReactSelect.optionProps => React.element;
};
module SelectOption = {
  module Styles = {
    let optionContainer =
      ReactDOM.Style.make(
        ~display="flex",
        ~alignItems="center",
        ~justifyContent="space-between",
        (),
      );
    let optionTextContainer =
      ReactDOM.Style.make(
        ~display="flex",
        ~flexGrow="1",
        ~alignItems="center",
        ~justifyContent="space-between",
        (),
      );
    let withOptionLabelBase =
      ReactDOM.Style.make(
        ~whiteSpace="nowrap",
        ~overflow="hidden",
        ~textOverflow="ellipsis",
        ~height="18px",
        ~lineHeight="20px",
      );
    let optionActiveUsers =
      ReactDOM.Style.make(
        ~fontSize="12px",
        ~lineHeight="14px",
        ~padding="0 4px",
        ~paddingLeft="10px",
        ~color=SharedStyles.Colors.textSecondary,
        ~height="12px",
        (),
      );
  };
  module Utils = {
    let formatActiveUsers = (value: int) =>
      value < 1000
        ? string_of_int(value)
        : (float_of_int(value) /. 1000.0 |> Printf.sprintf("%.1f")) ++ "K";
  };
  let render = (props: ReactSelect.optionProps) => {
    let innerRef = props.innerRef;
    let rawChildren = props.children;
    let getStyles = props.getStyles;
    let innerProps = props.innerProps;
    let defaultStyle = getStyles("option", props);
    let maxWidthLabel =
      props.data.extraFields.activeUsers
      |> Js.Nullable.toOption
      |> (
        fun
        | None => "190px"
        | Some(_) => "125px"
      );
    let optionLabelStyle =
      Styles.withOptionLabelBase(~maxWidth=maxWidthLabel, ());

    <Spread props=innerProps>
      <div
        ref=innerRef
        style={ReactDOM.Style.combine(defaultStyle, Styles.optionContainer)}>
        <Flag countryCode={props.data.value} />
        <div style=Styles.optionTextContainer>
          <div title={props.data.label} style=optionLabelStyle>
            rawChildren->Obj.magic
          </div>
          {switch (Js.Nullable.toOption(props.data.extraFields.activeUsers)) {
           | None => React.null
           | Some(activeUsers) =>
             <div style=Styles.optionActiveUsers>
               {activeUsers |> Utils.formatActiveUsers |> React.string}
             </div>
           }}
        </div>
      </div>
    </Spread>;
  };
};
