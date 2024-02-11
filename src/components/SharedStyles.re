module SharedStyles = {
  let makeStyleWithTextPrimary =
    ReactDOM.Style.make(
      ~fontFamily="Arial",
      ~fontSize="14px",
      ~fontStyle="normal",
      ~fontWeight="400",
    );
  module Colors = {
    let background = "#FFFFFF";
    let backgroundSelected = "#FFDBB3";
    let borderDark = "#00000033";
    let borderLight = "#00000014";
    let shadow = "rgba(0, 0, 0, 0.15)";
    let textPrimary = "#333333";
    let textSecondary = "#00000085";
    let textTertiary = "#00000052";
  };
};
