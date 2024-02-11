const fs = require('fs');
const path = require('path');

function copyDirSync(sourceDir, targetDir) {
  if (!fs.existsSync(targetDir)) {
    fs.mkdirSync(targetDir);
  }

  const entries = fs.readdirSync(sourceDir, { withFileTypes: true });

  for (const entry of entries) {
    const sourcePath = path.join(sourceDir, entry.name);
    const targetPath = path.join(targetDir, entry.name);

    if (entry.isFile()) {
      fs.copyFileSync(sourcePath, targetPath);
    }
    else if (entry.isDirectory()) {
      copyDirSync(sourcePath, targetPath);
    }
  }
}

function createDeployableArtifact() {
  const distDir = path.join(__dirname, '../dist');
  const deployDir = path.join(__dirname, '../deploy');
  const publicDir = path.join(__dirname, '../public');

  try {
    if (fs.existsSync(deployDir)) {
      fs.rmSync(deployDir, { recursive: true });
    }

    fs.mkdirSync(deployDir);

    copyDirSync(distDir, deployDir);

    fs.copyFileSync(path.join(publicDir, 'index.html'), path.join(deployDir, 'index.html'));

    console.log('Deployable artifact created successfully!');
  } catch (error) {
    console.error('Error creating deployable artifact:', error);
  }
}

createDeployableArtifact();
