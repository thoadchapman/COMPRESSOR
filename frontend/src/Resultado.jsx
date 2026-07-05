import { useApp } from './AppContext';
import { useState, useEffect } from 'react';

export default function Resultado() {
    const { compressa } = useApp();
    const [dicionario, setDicionario] = useState("");
    const [string, setString] = useState("");

    useEffect(() => {
        if (compressa) {
            const idx = compressa.indexOf("|");
            if (idx !== -1) {
                setDicionario(compressa.slice(0, idx));
                setString(compressa.slice(idx + 1));
            } else {
                setDicionario("");
                setString(compressa);
            }
        } else {
            setDicionario("");
            setString("");
        }
    }, [compressa]);

    if (!compressa) return null;

    const dictEntries = dicionario ? dicionario.split(',') : [];

    return (
        <div className="compressa-container">
            <div className="dictionary">
                {dictEntries.map((entry, index) => (
                    <div key={index} className="dict-entry">
                        {entry}
                    </div>
                ))}
            </div>
            <div className="compressed-string">
                {string}
            </div>
        </div>
    );
}