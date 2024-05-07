workspace {

    model {
        user = person "Field Engineer" "A user of my software system."
        softwareSystem = softwareSystem "Software System" "My software system." {
            webapp = container "Web Application"
            db = container "Data Base"
        }

        user -> webapp "uses"
        webapp -> db "reads from"
    }

    views {
        systemContext softwareSystem "SystemContext" {
            include *
            autoLayout
        }
        container softwareSystem "Diagram" {
            include *
            autoLayout
        }
        styles {
            element "Software System" {
                background #1168bd
                color #ffffff
            }
            element "Person" {
                shape person
                background #08427b
                color #ffffff
            }
        }
    }

}